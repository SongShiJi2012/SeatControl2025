@echo off
 rem 获取当前日期
set "currentDate=%date%"

rem 获取年份
set "year=%currentDate:~0,4%"

rem 获取月份
set "month=%currentDate:~5,2%"

rem 获取日期
set "day=%currentDate:~8,2%"

rem 设置当前年份是否为 2025 年
set /a "newYear=2025"
@date %newYear%-%month%-%day%

rem 定义源文件/目标文件路径以及文件名
set "SourceFolder=.\Appl_MassageMode_CtrlModel_ert_rtw\"
set "TargetFolder=..\..\..\DSM_P20_APP_KF32A156\sources\appl\MassageCtrl\"
set "FileName=Appl_MassageMode_CtrlModel"

rem 复制文件
copy /y "%SourceFolder%%FileName%.c" "%TargetFolder%%FileName%.c"
copy /y "%SourceFolder%%FileName%.h" "%TargetFolder%%FileName%.h"

rem 使用PowerShell修改复制文件的日期为当前日期 - 规避IDE更新旧日期文件的全编译
powershell -Command "(Get-Item '%TargetFolder%%FileName%.c').LastWriteTime = Get-Date"
powershell -Command "(Get-Item '%TargetFolder%%FileName%.h').LastWriteTime = Get-Date"

start  "" "%TargetFolder%"
rem pause