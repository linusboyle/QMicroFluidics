/**
 * newdesigndialog.h
 * Copyright (c) 2018 Linus Boyle <linusboyle@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
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
