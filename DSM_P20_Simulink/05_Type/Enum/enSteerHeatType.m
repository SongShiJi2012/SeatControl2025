%% Create enSteerHeatType enum

classdef enSteerHeatType < Simulink.IntEnumType

    enumeration
        EN_STEER_NONE(0)
        EN_STEER_OPEN(1)
        EN_STEER_CLOSE(2)
        EN_STEER_INVALID(3)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enSteerHeatType.EN_STEER_NONE;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '方向盘加热&#10;0x0:无动作&#10;0x1:开始&#10;0x2:关闭&#10;0x3:无效值,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
