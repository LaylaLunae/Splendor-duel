#ifndef PRIVILEGE_H
#define PRIVILEGE_H

#include <QPushButton>
#include <QWidget>
#include <QPen>

enum PrivilegeStatus {
    NONE = 0,
    POSSEDE = 1,
};

class Privilege {
public:
    Privilege(int id) : status(NONE),id(id) {}
    PrivilegeStatus getStatus()  ;
    void setStatus(PrivilegeStatus p);
    int getID() const;

private:
    PrivilegeStatus status;
    int id;
};
class VuePrivilege : public QPushButton {
    Q_OBJECT
public:
    VuePrivilege (const Privilege* p, QWidget *parent = nullptr):
            QPushButton(parent), parent(parent) {
        privilege = p;
        setFixedSize(50,50);
        connect(this,SIGNAL(clicked()),this,SLOT(clickedEvent()));
        QPalette palette = this->palette();
        palette.setColor(QPalette::Button, QColor("#FFB000"));
        palette.setColor(QPalette::ButtonText, Qt::black);
        setPalette(palette);
        setText("Privilège");
        update();
    };
//    explicit VuePrivilege(QWidget *parent = nullptr):QPushButton(parent){
//        setBackgroundRole(QPalette::Base);
//        setAutoFillBackground(true);
//        setFixedSize(50, 50);
//        connect(this, SIGNAL(clicked()), this, SLOT(clickedEvent()));
//        setCheckable(false);
//    };

    const Privilege* getPrivilege() const {
        return privilege;
    }

    void setPrivilege(const Privilege* p) {
        privilege = p;
    }


protected:
    void paintEvent(QPaintEvent *event) override;
private:
    const Privilege* privilege = nullptr;
    QWidget* parent;
    QPen pen;
    QBrush brush;
    signals:
            void privilegeClick(VuePrivilege*);
public slots:
private slots:
    void clickedEvent() { emit privilegeClick(this); }


};
#endif // PRIVILEGE_H
