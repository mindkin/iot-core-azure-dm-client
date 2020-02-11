# Build IoTDMClient Nuget Package



First you must build the solution in these configurations:

1. Release | ARM
2. Release | x86
3. Release | x64



Open the Visual Studio 2017 Command prompt.

Change directory to: `C:\Projects\github\mindkin\iot-core-azure-dm-client\nuget`

Execute this command:

```
PackIoTDMClientLib.cmd 1.1.0 Release
```

where the version number is what you want.