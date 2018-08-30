#ifndef NEWDESIGNDIALOG_H
#define NEWDESIGNDIALOG_H

#include <QDialog>

class QLineEdit;
class ConfigurationEntity;

class NewDesignDialog:public QDialog
{
    Q_OBJECT
public:
    explicit NewDesignDialog(QWidget* parent = nullptr);
    ~NewDesignDialog();

    void clearAll();
    ConfigurationEntity* getEntity() const;
private:
    void initUI();
    QLineEdit* sizeEdit;
    QLineEdit* input1Edit;
    QLineEdit* input2Edit;
    QLineEdit* output1Edit;
    QLineEdit* output2Edit;
    QLineEdit* output3Edit;

    ConfigurationEntity* entity;
private slots:
    void onConfirmed();
};

#endif // NEWDESIGNDIALOG_H
