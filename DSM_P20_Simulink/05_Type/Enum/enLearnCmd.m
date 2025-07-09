%% Create enLearnCmd enum

classdef enLearnCmd < Simulink.IntEnumType

    enumeration
        enNULL(0)
        enStartLearn(1)
        enStopLearn(2)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enLearnCmd.enNULL;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = 'enNULL（无效）&#10;enStartLearn （开始学习）&#10;enStopLearn（停止学习）,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
