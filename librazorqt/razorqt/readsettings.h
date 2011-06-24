#ifndef READSETTING_H
#define READSETTING_H

#include <QSettings>

#warning "ReadSettings is deprecated. Use RazorSettings instead."

/*! \brief Shared configuration handling.

Razor configuration is based on QSettings class.

This class, ReadSettings, opens one QSettings instance
based on INI file in the user home directory. ReadSettings
handles presence of the file too.

If there is no requested file found in the home directory the system-wide
installed file (see getSysPath()) is automatically copied into home
directory and then is it opened.

If there is no relevant system-wide file found the empty file is created.

ReadSettings user has to handle default values on their own. See
QSettings::value() default values.

\author Petr Vanek <petr@scribus.info>
*/
class ReadSettings : public QObject
{
    Q_OBJECT

public:
    /*! \brief Find and setup the configuration file.

    \param module a base name of the config file. It's a name without
            the extension. For example: if you want to open settings for
            panel call it as ReadSettings("panel"). Then access its
            settings over settings() method.
            The function will create all parent directories necessary to create
            the file.
            \note Existence of the QSettings instance is handled in this class.
                  Do not delete it on your own.
    \param parent It's no need to delete this class manually if it's set.
    */
    ReadSettings(const QString & module, QObject * parent = 0);
    ~ReadSettings() {};

    /*! \brief An access to QSettings object
    */
    QSettings* settings();

    const QString module() { return m_module; }

    /*! \brief Find location of the specified file or directory for Razor's cfg.
    The configuration is searched in more places:
      - user home dir (local config)
      - CMAKE_INSTALL_PREFIX location (the place set in the compilation time)
      - /usr/local/ prefix
      - /usr/ prefix
    It should handle all possibilities to get the requested file.
    \param fileName Name of the file including extension. Or name of the directory.
    */
    static QString getSysPath(const QString & fileName);

    /*! \brief Check existence of user config directory. Create it if it
    does not exist.
    */
    static bool checkConfigDir();

private:
    QSettings * m_settings;
    QString m_module;
};


/*! \brief Theme reader.
Theme contains QSS (a stylesheet description), icons, and background images.
All parts are optional.
ReadTheme search user home directory first, then the system-wide themes. See
ReadSettings::getSysPath() for more info.

\author Petr Vanek <petr@scribus.info>
*/
class ReadTheme : public QObject
{
    Q_OBJECT

public:
    /*! \brief Open, parse, and setup the GUI-theme.
    \param name a directory name of the theme
    \param parent No need to delete this object if it's set.
    */
    ReadTheme(const QString & name, QObject * parent = 0);
    /*! \brief Return QSS text (not-file, but real text).
    Paths in url() C/QSS functions are parsed to be real values for the theme,
    relative to full path
    */
    QString qss() { return m_qss; }

    /*! \brief A full path to image used as a wallpaper
     \param screen is an ID of the screen like in Qt. -1 means default (any) screen.
                   Any other value greater than -1 is the exact screen (in dualhead). 
		   In themes the index starts from 1 (ix 1 means 1st screen).
     \retval QString a file name (including path).
    */
    QString desktopBackground(int screen=-1);

private:
    QString m_qss;
    QString m_qssPath;
//    QHash<QString,QString> m_icons;
    QHash<int,QString> m_desktopBackgrounds;
};


#endif
