%% Create enSeatAutoRunSts enum

classdef enSeatAutoRunSts < Simulink.IntEnumType

    enumeration
        EN_SEAT_INVALID(0)
        EN_SEAT_RUNNING(1)
        EN_SEAT_SUCCESS(2)
        EN_SEAT_FAIL(3)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enSeatAutoRunSts.EN_SEAT_INVALID;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '座椅调用运动状态：&#10;0：Invalid&#10;1：Running&#10;2：Success&#10;3：Fail,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
