#include "newdesigndialog.h"
#include "configurationentity.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QIntValidator>

NewDesignDialog::NewDesignDialog(QWidget *parent):
    QDialog(parent),entity(nullptr)
{
    initUI();
}

NewDesignDialog::~NewDesignDialog() {
    if(entity){
        delete entity;
    }
}

void NewDesignDialog::initUI()
{
    //all the input lineedit widget
    sizeEdit = new QLineEdit(this);
    input1Edit = new QLineEdit(this);
    input2Edit = new QLineEdit(this);
    output1Edit = new QLineEdit(this);
    output2Edit = new QLineEdit(this);
    output3Edit = new QLineEdit(this);

    //set placeholder text
    sizeEdit->setPlaceholderText(tr("Equals number of rows and columns"));
    input1Edit->setPlaceholderText(tr("The index starts from 0"));
    input2Edit->setPlaceholderText(tr("The index starts from 0"));
    output1Edit->setPlaceholderText(tr("The index starts from 0"));
    output2Edit->setPlaceholderText(tr("The index starts from 0"));
    output3Edit->setPlaceholderText(tr("The index starts from 0"));

    //validator
    QIntValidator* validator = new QIntValidator(0,PIPE_SIZE_MAX,this);
    sizeEdit->setValidator(validator);
    input1Edit->setValidator(validator);
    input2Edit->setValidator(validator);
    output1Edit->setValidator(validator);
    output2Edit->setValidator(validator);
    output3Edit->setValidator(validator);

    //labels on side of lineedit
    QLabel* sizeHint = new QLabel(tr("Size:"),this);
    QLabel* input1Hint = new QLabel(tr("Input1 Pipe:"),this);
    QLabel* input2Hint = new QLabel(tr("Input2 Pipe:"),this);
    QLabel* output1Hint = new QLabel(tr("Output1 Pipe:"),this);
    QLabel* output2Hint = new QLabel(tr("Output2 Pipe:"),this);
    QLabel* output3Hint = new QLabel(tr("Output3 Pipe:"),this);

    //layouts to align lineedit and label
    QHBoxLayout* sizeLayout = new QHBoxLayout();
    QHBoxLayout* input1Layout = new QHBoxLayout();
    QHBoxLayout* input2Layout = new QHBoxLayout();
    QHBoxLayout* output1Layout = new QHBoxLayout();
    QHBoxLayout* output2Layout = new QHBoxLayout();
    QHBoxLayout* output3Layout = new QHBoxLayout();

    sizeLayout->addWidget(sizeHint);
    sizeLayout->addWidget(sizeEdit);
    input1Layout->addWidget(input1Hint);
    input1Layout->addWidget(input1Edit);
    input2Layout->addWidget(input2Hint);
    input2Layout->addWidget(input2Edit);
    output1Layout->addWidget(output1Hint);
    output1Layout->addWidget(output1Edit);
    output2Layout->addWidget(output2Hint);
    output2Layout->addWidget(output2Edit);
    output3Layout->addWidget(output3Hint);
    output3Layout->addWidget(output3Edit);

    //confirm and cancel button
    QPushButton* confirm = new QPushButton(tr("OK"),this);
    QPushButton* cancel = new QPushButton(tr("Cancel"),this);

    connect(confirm,&QPushButton::clicked,this,&NewDesignDialog::onConfirmed);
    connect(cancel,&QPushButton::clicked,this,&NewDesignDialog::reject);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(10);
    buttonLayout->addSpacing(100);
    buttonLayout->addWidget(confirm);
    buttonLayout->addWidget(cancel);

    //put all into groupbox
    QGroupBox* groupbox = new QGroupBox(tr("Configure New Design"),this);
    QVBoxLayout* groupLayout = new QVBoxLayout();
    groupLayout->addItem(sizeLayout);
    groupLayout->addItem(input1Layout);
    groupLayout->addItem(input2Layout);
    groupLayout->addItem(output1Layout);
    groupLayout->addItem(output2Layout);
    groupLayout->addItem(output3Layout);
    groupLayout->addItem(buttonLayout);
    groupbox->setLayout(groupLayout);

    //set the dialog layout
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(groupbox);
    setLayout(mainLayout);

    setFixedSize(300,400);
}

void NewDesignDialog::clearAll(){
    sizeEdit->clear();
    input1Edit->clear();
    input2Edit->clear();
    output1Edit->clear();
    output2Edit->clear();
    output3Edit->clear();
}

void NewDesignDialog::onConfirmed(){
    if(entity){
        delete entity;
    }
    entity = new ConfigurationEntity(sizeEdit->text().toInt(),input1Edit->text().toInt(),input2Edit->text().toInt(),
                                     output1Edit->text().toInt(),output2Edit->text().toInt(),output3Edit->text().toInt());
    this->accept();
}


ConfigurationEntity* NewDesignDialog::getEntity() const {
    return entity;
}
