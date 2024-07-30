
set MATLAB=D:\Matlab2020

cd .

if "%1"=="" ("D:\Matlab2020\bin\win64\gmake"  -f FOC_Ctrl_CodeModel.mk all) else ("D:\Matlab2020\bin\win64\gmake"  -f FOC_Ctrl_CodeModel.mk %1)
@if errorlevel 1 goto error_exit

exit 0

:error_exit
echo The make command returned an error of %errorlevel%
exit 1