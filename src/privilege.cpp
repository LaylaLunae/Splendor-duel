//
// Created by Pacino on 05/11/2023.
//
#include "../include/jeu.h"
//#include "../include/privilege.h"

PrivilegeStatus Privilege::getStatus() {
    return status;
}

void Privilege::setStatus(PrivilegeStatus p) {
    status = p;
}

int Privilege::getID() const {
    return id;
}


void VuePrivilege::paintEvent(QPaintEvent *event) {

    QPalette palette = this->palette();
    palette.setColor(QPalette::Button, Qt::white);
    setPalette(palette);
    QPushButton::paintEvent(event);
}