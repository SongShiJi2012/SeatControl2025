%% Create enHeatLvlSts enum

classdef enHeatLvlSts < Simulink.IntEnumType

    enumeration
        EN_HEAT_LVL_OFF(0)
        EN_HEAT_LVL_1(1)
        EN_HEAT_LVL_2(2)
        EN_HEAT_LVL_3(3)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enHeatLvlSts.EN_HEAT_LVL_OFF;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '¼ÓÈÈµµÎ»×´Ì¬:&#10;0£ºOFF&#10;1£ºLV1&#10;2£ºLV2&#10;3£ºLV3,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
