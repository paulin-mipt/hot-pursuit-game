mkdir ..\Release
mkdir ..\Release\Resources
cp ..\..\Externals\FreeGLUT\bin\freeglut.dll ..\Release
cp ..\..\Externals\StrategyDll.dll ..\Release
xcopy ..\..\Resources ..\Release\Resources /d /e /y
