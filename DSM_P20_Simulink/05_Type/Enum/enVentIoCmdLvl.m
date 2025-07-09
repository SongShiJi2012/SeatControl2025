%% Create enVentIoCmdLvl enum

classdef enVentIoCmdLvl < Simulink.IntEnumType

    enumeration
        EN_VENT_IO_LVL_NONE(0)
        EN_VENT_IO_LVL_OFF(1)
        EN_VENT_IO_LVL_1(2)
        EN_VENT_IO_LVL_2(3)
        EN_VENT_IO_LVL_3(4)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enVentIoCmdLvl.EN_VENT_IO_LVL_NONE;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '通风IO控制档位状态:&#10;0：无控制&#10;1：OFF&#10;2：LV1&#10;3：LV2&#10;4：LV3,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
