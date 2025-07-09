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
            desc = '加热故障&#10;0：无故障&#10;1：短路到地&#10;2：开路,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
