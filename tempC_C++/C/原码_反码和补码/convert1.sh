#!/bin/bash

# 原码转换为反码和补码的函数
convert_to_complement() {
    binary="$1"  # 输入的原码二进制字符串
    length=${#binary}  # 获取二进制字符串的长度

    # 计算反码
    complement=""
    for ((i = 0; i < length; i++)); do
        if [ "${binary:i:1}" == "0" ]; then
            complement+="1"
        else
            complement+="0"
        fi
    done

    # 计算补码
    carry=1
    for ((i = length - 1; i >= 0; i--)); do
        bit="${complement:i:1}"
        if [ "$carry" == "1" ]; then
            if [ "$bit" == "0" ]; then
                complement="${complement:0:i}1${complement:i+1}"
                carry=0
            else
                complement="${complement:0:i}0${complement:i+1}"
            fi
        fi
    done

    echo "原码： $binary"
    echo "反码： $complement"
    echo "补码： $complement"
}

# 输入原码二进制字符串
read -p "请输入原码的二进制表示（例如：1101）： " input

# 调用函数进行转换
convert_to_complement "$input"

