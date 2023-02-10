#ifndef BASE_COMPONENT_H
#define BASE_COMPONENT_H

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#include "utils/file_util.h"
#include "utils/string_util.h"
#include "utils/time_util.h"

class BaseComponent {
public:
    BaseComponent();

    virtual ~BaseComponent();

    virtual void ExportInfo();

    virtual std::string GetJsonInfo();

protected:
    FileUtil futil_;
    StringUtil sutil_;
    TimeUtil tutil_;

private:

};
#endif