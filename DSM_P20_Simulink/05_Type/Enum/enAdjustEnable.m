%% Create enAdjustEnable enum

classdef enAdjustEnable < Simulink.IntEnumType

    enumeration
        EN_Manual (0)
        EN_SixWayMotor (1)
        EN_TwelveWayMotor(2)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enAdjustEnable.EN_Manual;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '座椅调用调节配置：&#10;0x00:manual &#10;0x01:Six way motor &#10;0x02:Twelve way motor&#10;,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
