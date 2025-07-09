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
            desc = 'Í¨·çµµÎ»×´Ì¬:&#10;0£ºOFF&#10;1£ºLV1&#10;2£ºLV2&#10;3£ºLV3,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
