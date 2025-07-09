%% Create enNapMode enum

classdef enNapMode < Simulink.IntEnumType

    enumeration
        EN_NapMode_NULL(0)
        EN_NapMode_Close(1)
        EN_NapMode_Open(2)
        EN_NapMode_ERR(3)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enNapMode.EN_NapMode_NULL;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '小憩模式&#10;0x0:Inactive&#10;0x1:关闭小憩模式&#10;0x2:打开小憩模式&#10;0x3:ERROR,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
