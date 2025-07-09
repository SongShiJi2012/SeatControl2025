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
            desc = 'NTC����&#10;0���޹���&#10;1��NTC��·����&#10;2��NTC��·&#10;3��NTC�����Ŵ���,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
