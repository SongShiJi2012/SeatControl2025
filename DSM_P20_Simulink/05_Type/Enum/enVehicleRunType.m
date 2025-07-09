%% Create enVehicleRunType enum

classdef enVehicleRunType < Simulink.IntEnumType

    enumeration
        EN_HV_OFF(0)
        EN_HV_ON(1)
        EN_HV_READY(2)
        EN_HV_INVALID(3)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enVehicleRunType.EN_HV_OFF;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '整车运行状态:&#10;0x0:HV OFF&#10;0x1:HV ON&#10;0x2:Ready&#10;0x3:Invalid,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
