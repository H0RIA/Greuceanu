/*!
    \legalese

    Copyright 2017 Horia Popa

    Permission is hereby granted, free of charge, to any person obtaining a copy of this
    software and associated documentation files (the "Software"), to deal in the Software
    without restriction, including without limitation the rights to use, copy, modify,
    merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so, subject to the following conditions:


    The above copyright notice and this permission notice shall be included in all copies
    or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
    BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
    THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

    \endlegalese
*/

#ifndef BASE_H
#define BASE_H

/*
 * Decide here what version of web view to go with:
 *  - web engine (chromium)
 *  - webkit
 *
 *  Chromium DOES NOT support (yet) advanced network access (through the network access manager).
 *  Therefore we will not be supporting (actively) it for now!
 */

#define WEBVERSION_WEBKIT   0
#define WEBVERSION_CHROMIUM 1
#define CURRENT_WEBVERSION  WEBVERSION_CHROMIUM

#include <QApplication>
#include <QSettings>
#include <QScrollArea>
#include <QMouseEvent>
#include <QMainWindow>
#include <QFocusEvent>
#include <QShowEvent>
#include <QBitmap>
#include <QSvgRenderer>
#include <QHeaderView>
#include <QPainter>
#include <QFile>
#include <QIcon>
#include <QPixmap>
#include <QMessageBox>
#include <QDialog>
#include <QMenu>
#include <QContextMenuEvent>
#include <QNetworkCookie>
#include <QAction>
#include <QDateTime>
#include <QTextStream>
#include <QMutex>
#include <QDebug>
#include <QWidget>
#include <QLabel>
#include <QList>
#include <QListWidget>
#include <QTableView>
#include <QListView>
#include <QPushButton>
#include <QUuid>
#include <QThread>
#include <QCryptographicHash>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSystemTrayIcon>
#include <QGroupBox>
#include <QComboBox>
#include <QCheckBox>
#include <QDockWidget>
#include <QToolBar>
#include <QCloseEvent>
#include <QTableWidget>
#include <QStyle>
#include <QAbstractTableModel>
#include <QVariant>
#include <QTabWidget>
#include <QStandardItemModel>
#include <QPair>
#include <QStyledItemDelegate>
#include <QFontMetrics>
#include <QDesktopWidget>
#include <QNetworkProxy>
#include <QNetworkReply>
#include <QStackedWidget>
#include <QNetworkCookieJar>
#include <QUndoStack>

#include <QFileDialog>
#include <QShortcut>

#include <QNetworkAccessManager>
#include <QStringList>

#include <QDir>
#include <QMap>
#include <QFileInfo>
#include <QStandardPaths>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QtCore/qmath.h>
#include <QNetworkRequest>

#include <QUrl>
#include <QMovie>
#include <QLineEdit>
#include <QResizeEvent>

#if (CURRENT_WEBVERSION == WEBVERSION_CHROMIUM)
    #include <QtWebEngineWidgets/QtWebEngineWidgets>
#else
    #include <QWebHistory>
    #include <QWebFrame>
    #include <QWebElement>
    #include <QWebPage>
    #include <QWebSettings>
    #include <QWebView>
#endif

#include <sstream>

#ifndef MEMBER_NAME
#define MEMBER_NAME(name)     m_##name
#endif // !MEMBER_NAME

#ifndef MEMBER_NAME_PTR
#define MEMBER_NAME_PTR(name)     m_p##name
#endif // !MEMBER_NAME_PTR

#ifndef SETTER_NAME
#define SETTER_NAME(name)     set##name
#endif // !SETTER_NAME

#ifndef GETTER_NAME
#define GETTER_NAME(name)     name
#endif // !GETTER_NAME

#ifndef DECLARE_PROPERTY
#define DECLARE_PROPERTY(type, name)    \
    public:\
    inline type GETTER_NAME(name)()const{return MEMBER_NAME(name);}\
    inline void SETTER_NAME(name)(const type& value){MEMBER_NAME(name) = value;}\
    protected:\
    type    MEMBER_NAME(name);\

#endif // !DECLARE_PROPERTY

#ifndef DECLARE_PROPERTY_PTR
#define DECLARE_PROPERTY_PTR(type, name)    \
    public:\
    inline type* GETTER_NAME(name)()const{return MEMBER_NAME_PTR(name);}\
    inline void SETTER_NAME(name)(type* value){MEMBER_NAME_PTR(name) = value;}\
    protected:\
    type*    MEMBER_NAME_PTR(name);\

#endif // !DECLARE_PROPERTY_PTR

#ifndef DECLARE_PROPERTY_GREF
#define DECLARE_PROPERTY_GREF(type, name)    \
    public:\
    inline const type& GETTER_NAME(name)()const{return MEMBER_NAME(name);}\
    inline type& GETTER_NAME(name)(){return MEMBER_NAME(name);}\
    inline void SETTER_NAME(name)(const type& value){MEMBER_NAME(name) = value;}\
    protected:\
    type    MEMBER_NAME(name);\

#endif // !DECLARE_PROPERTY_GREF

#ifndef DECLARE_EQ_OPERATORS
#define DECLARE_EQ_OPERATORS(name)  \
    bool operator==(const name& value)const;\
    bool operator!=(const name& value)const;\

#endif // !DECLARE_EQ_OPERATORS

#ifndef DECLARE_ASSIGN_OPERATOR
#define DECLARE_ASSIGN_OPERATOR(name)  \
    name& operator=(const name& value);\

#endif // !DECLARE_ASSIGN_OPERATOR

#ifndef DECLARE_DEFAULT_CONSTRUCTOR
#define DECLARE_DEFAULT_CONSTRUCTOR(name)\
    name();\

#endif // !DECLARE_DEFAULT_CONSTRUCTOR

#ifndef DECLARE_COPY_CONSTRUCTOR
#define DECLARE_COPY_CONSTRUCTOR(name)\
    name(const name& obj);\

#endif // !DECLARE_COPY_CONSTRUCTOR

#ifndef DECLARE_DESTRUCTOR
#define DECLARE_DESTRUCTOR(name)\
    virtual ~name();\

#endif // !DECLARE_DESTRUCTOR

#ifndef DECLARE_DEF_METHODS
#define DECLARE_DEF_METHODS(name)\
    DECLARE_DEFAULT_CONSTRUCTOR(name)\
    DECLARE_COPY_CONSTRUCTOR(name)\
    DECLARE_DESTRUCTOR(name)\

#endif // !DECLARE_DEF_METHODS

#ifndef DECLARE_AS_SINGLETON
#define DECLARE_AS_SINGLETON(name)\
    Q_DISABLE_COPY(name)\
    public:\
        static name* instance();\
        virtual ~name();\
    private:\
        name();\
    private:\
        static name* m_pInstance;

#endif // !DECLARE_AS_SINGLETON

#ifndef IMPLEMENT_SINGLETON
#define IMPLEMENT_SINGLETON(name)\
    name* name::m_pInstance = nullptr;\
    name* name::instance()\
    {\
        if(m_pInstance == nullptr){\
            m_pInstance = new name();\
        }\
        return m_pInstance;\
    }

#endif // !IMPLEMENT_SINGLETON

namespace Core
{
    /**
     * @brief
     *
     * @param path
     * @return QByteArray
     */
    inline QByteArray loadFileContent(const QString& path)
    {
        QByteArray buffer;

        if(path.isEmpty())
            return buffer;

        QFile file(path);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
            buffer = file.readAll();
            file.close();
        }

        return buffer;
    }
}

#endif // BASE_H
