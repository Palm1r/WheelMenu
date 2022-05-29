#include "wheelMenuModel.h"

#include <QRandomGenerator>
#include <QXmlStreamWriter>

namespace model {

const QString &Path = QString("%1/conf.xml").arg(SAVE_PATH);

WheelMenuModel::WheelMenuModel(QObject *parent)
    : QAbstractListModel{parent}
    , m_innerRowIndex(-1)
{
    startTimer(5000);

    auto menuItemFactory = [](const QString &name, const QString &color) {
        QList<ListItem> listItems;
        int rand = QRandomGenerator::global()->bounded(3, 12);
        for (int i = 0; i < rand; ++i) {
            listItems.append(ListItem{color});
        }
        return MenuItem{name, color, listItems};
    };

    addMenuItem(std::move(menuItemFactory("name-red", "red")));
    addMenuItem(std::move(menuItemFactory("name-orange", "orange")));
    addMenuItem(std::move(menuItemFactory("name-yellow", "yellow")));
    addMenuItem(std::move(menuItemFactory("name-green", "green")));
    addMenuItem(std::move(menuItemFactory("name-cyan", "cyan")));
    addMenuItem(std::move(menuItemFactory("name-blue", "blue")));
    addMenuItem(std::move(menuItemFactory("name-violet", "violet")));
}

int WheelMenuModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return m_menuItems.size();
}

QVariant WheelMenuModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    const auto &menuItem = m_menuItems.at(index.row());
    switch (role) {
    case NameRole:
        return menuItem->m_name;
    case ColorRole:
        return menuItem->m_color;
    case OuterRowIndexRole:
        return menuItem->m_outerRowIndex;
    case ListRole:
        return QVariant::fromValue(menuItem->m_internalList);
    default:
        return QVariant();
    }
}

bool WheelMenuModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        const auto &menuItem = m_menuItems.at(index.row());
        switch (role) {
        case OuterRowIndexRole:
            menuItem->m_outerRowIndex = value.toInt();
            break;
        default:
            qDebug() << "role no support for change";
        }
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

QHash<int, QByteArray> WheelMenuModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[NameRole] = "menuItemName";
    roles[ColorRole] = "menuItemColor";
    roles[OuterRowIndexRole] = "outerRowIndex";
    roles[ListRole] = "menuItemInternalList";

    return roles;
}

void WheelMenuModel::addMenuItem(MenuItem &&item)
{
    beginInsertRows(QModelIndex(), m_menuItems.size(), m_menuItems.size());

    MenuItemPtr newItem(new MenuItem(item));
    m_menuItems.emplace_back(std::move(newItem));

    endInsertRows();
}

void WheelMenuModel::timerEvent(QTimerEvent *event)
{
    std::vector<MenuItemPtr> menuItemsCopy;
    menuItemsCopy.reserve(m_menuItems.size());

    int innerRowIndexCopy = m_innerRowIndex;

    std::transform(m_menuItems.begin(),
                   m_menuItems.end(),
                   std::back_inserter(menuItemsCopy),
                   [](const auto &menuItem) {
                       return std::unique_ptr<MenuItem>(new MenuItem(*menuItem));
                   });

    std::thread save_thread([&menuItemsCopy, innerRowIndexCopy]() {
        QFile file(Path);

        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QXmlStreamWriter xmlWriter(&file);
            xmlWriter.setAutoFormatting(true);
            xmlWriter.writeStartDocument();
            xmlWriter.writeStartElement("wheelMenuConfig");
            xmlWriter.writeAttribute("innerRowIndex", QString("%1").arg(innerRowIndexCopy));
            xmlWriter.writeStartElement("MenuItems");
            for (const auto &menuItem : menuItemsCopy) {
                xmlWriter.writeTextElement("name", QString("%1").arg(menuItem->m_name));
                xmlWriter.writeTextElement("icon", QString("%1").arg(menuItem->m_color));
                xmlWriter.writeTextElement("index", QString("%1").arg(menuItem->m_outerRowIndex));
                xmlWriter.writeStartElement("ListItems");
                for (const auto &listItem : menuItem->m_internalList) {
                    xmlWriter.writeTextElement("icon", QString("%1").arg(listItem.m_color));
                }
                xmlWriter.writeEndElement();
            }
            xmlWriter.writeEndElement();

            xmlWriter.writeEndElement();
            xmlWriter.writeEndDocument();
            file.close();
        } else {
            qDebug() << "error to write";
        }
    });
    save_thread.join();
}
} // namespace model
