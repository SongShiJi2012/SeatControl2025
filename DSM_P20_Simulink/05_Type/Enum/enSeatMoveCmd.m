%% Create enSeatMoveCmd enum

classdef enSeatMoveCmd < Simulink.IntEnumType

    enumeration
        EN_NULL(0)
        EN_UP_FORWARD(1)
        EN_DN_BACKWARD(2)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enSeatMoveCmd.EN_NULL;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '�����������&#10;0 : ������&#10;1 : ����/��ǰ&#10;2 : ����/���,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
