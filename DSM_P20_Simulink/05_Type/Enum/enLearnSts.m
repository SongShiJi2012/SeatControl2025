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
            desc = '0x0:enNull;(无学习)&#10;0x1:enLearnning;（学习中）&#10;0x2:enLearnAllSuccess;（学习成功）,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
