%% Create enLearnSts enum

classdef enLearnSts < Simulink.IntEnumType

    enumeration
        enNULL(0)
        enLearnning(1)
        enLearnAllSuccess(2)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enLearnSts.enNULL;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '0x0:enNull;(��ѧϰ)&#10;0x1:enLearnning;��ѧϰ�У�&#10;0x2:enLearnAllSuccess;��ѧϰ�ɹ���,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
