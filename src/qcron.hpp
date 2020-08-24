#ifndef _QCRON_HPP
#define _QCRON_HPP

#include <QObject>
#include <QDateTime>
#include "qcronfield.hpp"

class QCron : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(QString pattern READ pattern WRITE setPattern NOTIFY patternChanged)
public:
    QCron();
    QCron(const QString & pattern);
    ~QCron();

    bool enabled() const
        { return _enabled; }

    void setEnabled(bool enabled);

    const QString &pattern() const;
    void setPattern(const QString &pattern);

    // Accessors.
    Q_INVOKABLE bool isValid() const
        { return _is_valid; }

    Q_INVOKABLE const QString & error() const
        { return _error; }

    // Features.

    Q_INVOKABLE QDateTime next();
    Q_INVOKABLE QDateTime next(QDateTime dt);
    void catchUp(QDateTime & dt, EField field, int value);
    Q_INVOKABLE bool match(const QDateTime & dt) const;
    void add(QDateTime & dt, EField field, int value);

signals:
    void enabledChanged();
    void patternChanged();

    void activated();
    void triggered();
    void deactivated();

    void patternError(const QString &errorMessage);

private:
    bool _enabled;
    QString _pattern;
    bool _is_valid;
    bool _is_active;
    QString _error;
    QCronField _fields[6];

    void _init();
    void _setError(const QString & error);
    void _parsePattern(const QString & pattern);
    void _parseField(QString & field_str,
                     EField field);
    QString _validCharacters(EField field);
    void _process(QDateTime & dt, EField field);

private slots:
    void _checkState();
};

#endif
