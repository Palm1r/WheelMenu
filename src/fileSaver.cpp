#include "fileSaver.h"

using namespace model;
const QString &Path = QString("%1/conf.xml").arg(SAVE_PATH);

FileSaver::FileSaver()
    : m_pingPong{&m_menuItemsCopyPing, &m_menuItemsCopyPong}
{}

void FileSaver::copyData(ModelData modelData)
{
    int writeIndex = m_currentIndex == 0 ? 1 : 0;

    std::vector<std::unique_ptr<MenuItem>> *writeBuffer = m_pingPong[writeIndex];

    writeBuffer->clear();
    std::transform(modelData.first->begin(),
                   modelData.first->end(),
                   std::back_inserter(*writeBuffer),
                   [](const auto &menuItem) {
                       return std::unique_ptr<MenuItem>(new MenuItem(*menuItem));
                   });

    m_innerRowIndexCopy = modelData.second;

    if (m_mutex.tryLock()) {
        m_currentIndex = m_currentIndex == 0 ? 1 : 0;
        m_mutex.unlock();
    }
}

void FileSaver::saveConfig()
{
    QMutexLocker locker(&m_mutex);

    const auto items = m_pingPong[m_currentIndex];
    if (items->size() == 0) {
        return;
    }

    QFile file(Path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QXmlStreamWriter xmlWriter(&file);
        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("wheelMenuConfig");
        xmlWriter.writeAttribute("innerRowIndex", QString("%1").arg(m_innerRowIndexCopy));
        xmlWriter.writeStartElement("MenuItems");
        for (const auto &menuItem : *items) {
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

    emit savedFinished();
}
