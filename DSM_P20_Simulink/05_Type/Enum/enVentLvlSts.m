%% Create enVentLvlSts enum

classdef enVentLvlSts < Simulink.IntEnumType

    enumeration
        EN_VENT_LVL_OFF(0)
        EN_VENT_LVL_1(1)
        EN_VENT_LVL_2(2)
        EN_VENT_LVL_3(3)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enVentLvlSts.EN_VENT_LVL_OFF;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = 'ͨ�絵λ״̬:&#10;0��OFF&#10;1��LV1&#10;2��LV2&#10;3��LV3,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
