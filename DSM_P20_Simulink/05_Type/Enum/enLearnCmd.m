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
            desc = 'enNULL����Ч��&#10;enStartLearn ����ʼѧϰ��&#10;enStopLearn��ֹͣѧϰ��,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
