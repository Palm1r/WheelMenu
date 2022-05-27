#ifndef WHEELMENUMODEL_H
#define WHEELMENUMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QtQml>

namespace model {
struct MenuItem
{
    QString m_name;
    QString m_color;
    QList<QVariant> m_internalList = QVariantList();
};

class WheelMenuModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int lastActiveIndex MEMBER m_lastActiveIndex NOTIFY lastActiveIndexChanged)

    QML_ELEMENT
public:
    using MenuItemPtr = std::unique_ptr<MenuItem>;

    enum Roles { MenuItemNameRole = Qt::UserRole, ColorRole, ListRole };

    explicit WheelMenuModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    void addMenuItem(const MenuItem &item);

signals:
    void lastActiveIndexChanged();

private:
    std::vector<MenuItemPtr> m_menuItems;
    int m_lastActiveIndex;
};
} // namespace model

#endif // WHEELMENUMODEL_H
