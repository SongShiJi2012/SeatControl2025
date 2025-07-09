%% Create enProjectType enum

classdef enProjectType < Simulink.IntEnumType

    enumeration
        EN_PROJECT_P20(0)
        EN_PROJECT_BM400(1)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enProjectType.EN_PROJECT_P20;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '��Ŀ����&#10;0��P20����&#10;1��BM400����,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
