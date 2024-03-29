#include "../include/jeu.h"

PrivilegeStatus Privilege::getStatus()  {
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
    palette.setColor(QPalette::Button, QColor("beige"));
    palette.setColor(QPalette::ButtonText, Qt::black);
    setPalette(palette);
//    QPalette palette = this->palette();
//    palette.setColor(QPalette::Button, Qt::white);
//    setPalette(palette);
    QPushButton::paintEvent(event);
}