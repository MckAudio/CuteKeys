#ifndef NATIVEOBJECT_H
#define NATIVEOBJECT_H

#include <QObject>

class NativeObject : public QObject
{
    Q_OBJECT
public:
    explicit NativeObject(QObject *parent = nullptr);
    Q_PROPERTY(QString text READ getText WRITE setText);
    const QString& getText() { return m_text; };
    void setText(QString& text);
private:
    QString m_text;
};

#endif // NATIVEOBJECT_H
