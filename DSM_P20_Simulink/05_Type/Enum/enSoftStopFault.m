%% Create enSoftStopFault enum

classdef enSoftStopFault < Simulink.IntEnumType

    enumeration
        EN_NULL_STOP(0)
        EN_UP_FORWARD_STOP(1)
        EN_DN_BACKWARD_STOP(2)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enSoftStopFault.EN_NULL_STOP;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '到达那个方向&#10;0：无&#10;1：上、前&#10;2：下、后,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
