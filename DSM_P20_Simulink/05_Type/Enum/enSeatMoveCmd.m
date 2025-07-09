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
            desc = '电机控制命令&#10;0 : 无命令&#10;1 : 向上/向前&#10;2 : 向下/向后,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
