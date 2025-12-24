#include "Message.h"
#include <iostream>

void swap(Message &lhs,Message &rhs)
{
    using std::swap;
    lhs.remove_from_Folders(); //clear left hand side resources
    rhs.remove_from_Folders();

    swap(lhs.folders,rhs.folders);
    swap(lhs.contents,rhs.contents);

    lhs.add_to_folders(); //将message中的folder重新添加本对象

}