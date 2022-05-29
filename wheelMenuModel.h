#ifndef WHEELMENUMODEL_H
#define WHEELMENUMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QtQml>

namespace model {
struct ListItem
{
    Q_GADGET

    Q_PROPERTY(QString color MEMBER m_color CONSTANT)
public:
    QString m_color;
};

struct MenuItem
{
    QString m_name;
    QString m_color;
    QList<ListItem> m_internalList;
    int m_outerRowIndex = 0;
};

class WheelMenuModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int innerRowIndex MEMBER m_innerRowIndex NOTIFY innerRowIndexChanged)

    QML_ELEMENT
public:
    using MenuItemPtr = std::unique_ptr<MenuItem>;

    enum Roles { NameRole = Qt::UserRole, ColorRole, ListRole, OuterRowIndexRole };

    explicit WheelMenuModel(QObject *parent = nullptr);
    ~WheelMenuModel() = default;

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QHash<int, QByteArray> roleNames() const override;

    void addMenuItem(MenuItem &&item);

signals:
    void innerRowIndexChanged();

private:
    std::vector<MenuItemPtr> m_menuItems;
    int m_innerRowIndex;
};
} // namespace model

Q_DECLARE_METATYPE(model::ListItem)
#endif // WHEELMENUMODEL_H
