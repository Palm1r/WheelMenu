#ifndef WHEELMENUMODEL_H
#define WHEELMENUMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QtQml>

class FileSaver;
namespace model {

//item for one and grid pages with content
struct ListItem
{
    Q_GADGET

    Q_PROPERTY(QString color MEMBER m_color CONSTANT)
public:
    QString m_color; //  instead any content
};

// inner row item with icon
struct MenuItem
{
    QString m_name;
    QString m_color; // instead any icon
    //for further optimization, we can replace the QList<> to another one abstract list model and mapping data between theirs
    QList<ListItem> m_internalList;
    int m_outerRowIndex = 0;
};

// data model for Menu Item
class WheelMenuModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(
        int innerRowIndex READ innerRowIndex WRITE setInnerRowIndex NOTIFY innerRowIndexChanged)

    QML_ELEMENT
public:
    using MenuItemPtr = std::unique_ptr<MenuItem>;

    enum Roles { NameRole = Qt::UserRole, ColorRole, ListRole, OuterRowIndexRole };

    // override default function
    explicit WheelMenuModel(QObject *parent = nullptr);
    ~WheelMenuModel();

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QHash<int, QByteArray> roleNames() const override;

    void addMenuItem(MenuItem &&item);

    int innerRowIndex() const;
    void setInnerRowIndex(int newInnerRowIndex);

signals:
    void innerRowIndexChanged();
    void startSaveConfig();

private:
    std::vector<MenuItemPtr> m_menuItems;
    int m_innerRowIndex;
    QThread *m_saveThread;
    FileSaver *m_saveWorker;
    QTimer *m_configSaveTimer;
};
} // namespace model

Q_DECLARE_METATYPE(model::ListItem)
#endif // WHEELMENUMODEL_H
