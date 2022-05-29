#include "wheelMenuModel.h"
#include <QRandomGenerator>

namespace model {

WheelMenuModel::WheelMenuModel(QObject *parent)
    : QAbstractListModel{parent}
    , m_innerRowIndex(-1)
{
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
    m_menuItems.push_back(std::move(newItem));

    endInsertRows();
}
} // namespace model