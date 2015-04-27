#ifndef ARGACTION_H
#define ARGACTION_H

#include <QMap>
#include <QString>
#include <QStringList>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QComboBox>

template <class T1, class T2> class QWidgetPair : public QWidget
{
public:
    explicit QWidgetPair() {}
    explicit QWidgetPair(T1 *object1, T2 *object2) :
       object1(object1), object2(object2) {}

    T1 *object1;
    T2 *object2;
};

class argAction
{
protected:
    static bool setDoubleSpinBox(void *doubleSpinBox, const QString argValue);
    static bool setSpinBox(void *spinBox, const QString argValue);
    static bool setCheckBox(void *checkBox, const QString argValue);
    static bool setLineEdit(void *lineEdit, const QString argValue);
    static bool setComboBox(void *comboBox, const QString argValue);
    static bool setRadioButtonPair(void *radioButtonPair, const QString argValue);

    static QString getDoubleSpinBox(void *doubleSpinBox);
    static QString getSpinBox(void *spinBox);
    static QString getCheckBox(void *checkBox);
    static QString getLineEdit(void *lineEdit);
    static QString getComboBox(void *comboBox);
    static QString getRadioButtonPair(void *radioButtonPair);

    struct argElement
    {
        bool (*setFunction)(void *object, QString argValue);
        QString (*getFunction)(void *object);
        void *object;
    };

    QMap<QString,argElement> argList;

public:
    explicit argAction();
    ~argAction();

    bool setValue(const QString key, const QString value);
    QStringList getAllArgs(const QString prepend, bool getCommentedOptions);
    bool setEnabled(const QString key, const bool enabled);

    inline void insert( const QString argName, QDoubleSpinBox *doubleSpinBox )
    {
        argList.insert( argName, (argElement){ .setFunction = &setDoubleSpinBox, .getFunction = &getDoubleSpinBox,
                                               .object = doubleSpinBox } );
    }

    inline void insert( const QString argName, QSpinBox *spinBox)
    {
        argList.insert( argName, (argElement){ .setFunction = &setSpinBox, .getFunction = &getSpinBox,
                                               .object = spinBox } );
    }

    inline void insert( const QString argName, QCheckBox *checkBox)
    {
        argList.insert( argName, (argElement){ .setFunction = &setCheckBox, .getFunction = &getCheckBox,
                                               .object = checkBox } );
    }

    inline void insert( const QString argName, QLineEdit *lineEdit)
    {
        argList.insert( argName, (argElement){ .setFunction = &setLineEdit, .getFunction = &getLineEdit,
                                               .object = lineEdit } );
    }

    inline void insert( const QString argName, QComboBox *comboBox)
    {
        argList.insert( argName, (argElement){ .setFunction = &setComboBox, .getFunction = &getComboBox,
                                               .object = comboBox } );
    }

    inline void insert( const QString argName, QWidgetPair<QRadioButton, QRadioButton> *radioButtonPair)
    {
        argList.insert( argName, (argElement){ .setFunction = &setRadioButtonPair, .getFunction = &getRadioButtonPair,
                                               .object = radioButtonPair } );
    }
};

#endif // ARGACTION_H