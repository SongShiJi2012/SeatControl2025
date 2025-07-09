%% Create enHeatCmdFault enum

classdef enHeatCmdFault < Simulink.IntEnumType

    enumeration
        EN_HEAT_FAULT_NONE(0)
        EN_HEAT_FAULT_GND(1)
        EN_HEAT_FAULT_OPEN(2)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enHeatCmdFault.EN_HEAT_FAULT_NONE;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '���ȹ���&#10;0���޹���&#10;1����·����&#10;2����·,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
