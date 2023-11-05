#ifndef PRIVILEGE_H
#define PRIVILEGE_H

enum PrivilegeStatus {
    NONE = 0,
    POSSEDE = 1,
};

class Privilege {
public:
    Privilege() : status(NONE) {} // 构造函数初始化为NONE状态
    PrivilegeStatus getStatus();
    void setStatus(PrivilegeStatus p);

private:
    PrivilegeStatus status; // 成员变量表示特权状态
};

#endif // PRIVILEGE_H
