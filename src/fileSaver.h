#ifndef FILESAVER_H
#define FILESAVER_H

#include "wheelMenuModel.h"
#include <QMutex>
#include <QObject>

class FileSaver : public QObject
{
    Q_OBJECT
public:
    using ModelData = std::pair<std::vector<std::unique_ptr<model::MenuItem>> *, int>;
    using MenuItemPtr = std::unique_ptr<model::MenuItem>;

    explicit FileSaver();
    ~FileSaver() = default;

    void copyData(ModelData modelData);

public slots:
    void saveConfig();

signals:
    void savedFinished();

private:
    std::vector<MenuItemPtr> m_menuItemsCopyPing;
    std::vector<MenuItemPtr> m_menuItemsCopyPong;

    int m_innerRowIndexCopy = 0;
    QMutex m_mutex;

    std::vector<MenuItemPtr> *m_pingPong[2];
    std::size_t m_currentIndex = 0;
};

#endif // FILESAVER_H
