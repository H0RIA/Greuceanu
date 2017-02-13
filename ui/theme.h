#ifndef THEME
#define THEME

#include "base.h"

namespace UI
{
    class Theme
    {
        public:
            Theme(const QString& path = QString());
            Theme(const Theme& theme);
            virtual ~Theme();

            void addCssFile(const QString& path);
            void clearFiles();
            void remCssFile(const QString& path);

            Theme& operator=(const Theme& theme);
            bool operator==(const Theme& theme)const;
            bool operator!=(const Theme& theme)const;

            QByteArray load()const;

        protected:
            QList<QString> m_ThemeFiles;
    };
}

#endif // THEME

