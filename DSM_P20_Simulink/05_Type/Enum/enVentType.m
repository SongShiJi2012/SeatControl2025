%% Create enVentType enum

classdef enVentType < Simulink.IntEnumType

    enumeration
        EN_VENT_TYPE_NONE(0)
        EN_VENT_TYPE_HMI(1)
        EN_VENT_TYPE_TBOX(2)
        EN_VENT_TYPE_DIAG(3)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enVentType.EN_VENT_TYPE_NONE;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '通风类型&#10;0：无&#10;1：HMI&#10;2：Tbox&#10;3：诊断,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
