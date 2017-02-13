#include "theme.h"

using namespace UI;

Theme::Theme(const QString& path)
    :   m_ThemeFiles()
{
    m_ThemeFiles.append(path);
}

Theme::Theme(const Theme& theme)
    :   m_ThemeFiles(theme.m_ThemeFiles)
{}

Theme::~Theme()
{
}

void
Theme::addCssFile(const QString& path)
{
    if(!m_ThemeFiles.contains(path))
        m_ThemeFiles.append(path);
}

void
Theme::clearFiles()
{
    m_ThemeFiles.clear();
}

void
Theme::remCssFile(const QString& path)
{
    m_ThemeFiles.removeOne(path);
}

Theme&
Theme::operator=(const Theme& theme)
{
    m_ThemeFiles.clear();
    m_ThemeFiles = theme.m_ThemeFiles;

    return *this;
}

bool
Theme::operator==(const Theme& theme)const
{
    if(m_ThemeFiles.size() != theme.m_ThemeFiles.size())
        return false;

    for(int index = 0; index < m_ThemeFiles.size(); index++){
        if(theme.m_ThemeFiles.at(index) != m_ThemeFiles.at(index))
            return false;
    }

    return true;
}

bool
Theme::operator!=(const Theme& theme)const
{
    return !(this->operator ==(theme));
}

QByteArray
Theme::load()const
{
    QByteArray data;

    foreach(QString path, m_ThemeFiles){
        if(!path.isEmpty()){
            QFileInfo fi(path);
            if(fi.exists() && fi.isFile()){
                QFile file(path);
                if(file.open(QIODevice::ReadOnly)){
                    data += file.readAll();
                    file.close();
                }else{
                    qDebug() << "Could not read theme file: " << file.errorString();
                }
            }
        }
    }

    return data;
}

