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

    void addMenuItem(const MenuItem &item);

signals:
    void innerRowIndexChanged();

private:
    std::vector<MenuItemPtr> m_menuItems;
    int m_innerRowIndex;
};
} // namespace model

#endif // WHEELMENUMODEL_H
