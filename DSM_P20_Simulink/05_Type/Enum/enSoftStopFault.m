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
            desc = '�����Ǹ�����&#10;0����&#10;1���ϡ�ǰ&#10;2���¡���,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
