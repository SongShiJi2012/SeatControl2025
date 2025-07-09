%% Create enDrAdjustEnable enum

classdef enDrAdjustEnable < Simulink.IntEnumType

    enumeration
        EN_DrManual (0)
        EN_DrSixWayMotor (1)
        EN_DrTwelveWayMotor(2)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enDrAdjustEnable.EN_DrManual;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '主驾座椅调用调节配置：&#10;0x00:manual &#10;0x01:Six way motor &#10;0x02:Twelve way motor,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
