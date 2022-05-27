#include "wheelMenuModel.h"

namespace model {

WheelMenuModel::WheelMenuModel(QObject *parent)
    : QAbstractListModel{parent}
{
    addMenuItem({"red", "red", {1, 2, 3}});
    addMenuItem({"orange", "orange", {4, 5, 6, 7, 8, 9}});
    addMenuItem({"yellow", "yellow", {7, 8, 9, 0}});
    addMenuItem({"green", "green"});
    addMenuItem({"cyan", "cyan"});
    addMenuItem({"blue", "blue"});
    addMenuItem({"violet", "violet"});
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
    case MenuItemNameRole:
        return menuItem->m_name;
    case ColorRole:
        return menuItem->m_color;
    case ListRole:
        return menuItem->m_internalList;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> WheelMenuModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[MenuItemNameRole] = "menuItemName";
    roles[ColorRole] = "menuItemColor";
    roles[ListRole] = "menuItemInternalList";

    return roles;
}

void WheelMenuModel::addMenuItem(const MenuItem &item)
{
    beginInsertRows(QModelIndex(), m_menuItems.size(), m_menuItems.size());

    MenuItemPtr newItem(new MenuItem(item));
    m_menuItems.push_back(std::move(newItem));

    endInsertRows();
}
} // namespace model
