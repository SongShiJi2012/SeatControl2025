%% Create enMotorLearn enum

classdef enMotorLearn < Simulink.IntEnumType

    enumeration
        EN_NULL(0)
        EN_LearnHeight(1)
        EN_LearnLength(2)
        EN_LearnBack(3)
        EN_LearnFront(4)
        EN_LearnReset(5)
        EN_LearnSuccess(6)
        EN_LearnFault(7)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enMotorLearn.EN_NULL;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = 'ѧϰ״̬��&#10;0x0:null&#10;0x01:Height Learn&#10;0x02:Length Learn&#10;0x03:Back Learn&#10;0x04:Front Learn&#10;0x05:Learn Reset&#10;0x06:Learn Success&#10;0x07:Learn Fault,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
