%% Create enVentCmdFault enum

classdef enVentCmdFault < Simulink.IntEnumType

    enumeration
        EN_VENT_FAULT_NONE(0)
        EN_VENT_FAULT_OPEN(1)
        EN_VENT_FAULT_LOAD(2)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enVentCmdFault.EN_VENT_FAULT_NONE;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '通风故障&#10;0：无&#10;1：开路&#10;2：短电源,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
