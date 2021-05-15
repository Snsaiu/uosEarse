#ifndef PERMISSIONTYPE_H
#define PERMISSIONTYPE_H


enum PermissionType{
    USER=0, //普通用户
    SYS_MANAGER=1, // 系统管理员
    SAFE_MANAGER=2, // 安全保密管理员
    AUDIT_MANAGER=3, //审计员
};


#endif // PERMISSIONTYPE_H
