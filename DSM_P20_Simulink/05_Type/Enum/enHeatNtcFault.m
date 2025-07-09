%% Create enHeatNtcFault enum

classdef enHeatNtcFault < Simulink.IntEnumType

    enumeration
        EN_NTC_FAULT_NONE(0)
        EN_NTC_FAULT_GND(1)
        EN_NTC_FAULT_OPEN(2)
        EN_NTC_FAULT_UNC(3)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enHeatNtcFault.EN_NTC_FAULT_NONE;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = 'NTC故障&#10;0：无故障&#10;1：NTC短路到地&#10;2：NTC开路&#10;3：NTC不可信错误,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
