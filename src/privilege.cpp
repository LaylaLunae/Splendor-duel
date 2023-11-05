//
// Created by Pacino on 05/11/2023.
//

#include "../include/privilege.h"

PrivilegeStatus Privilege::getStatus() {
    return status;
}

void Privilege::setStatus(PrivilegeStatus p) {
    status = p;
}