%% Create enVehTypePrm enum

classdef enVehTypePrm < Simulink.IntEnumType

    enumeration
        enP20(0)
        enBM400(1)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enVehTypePrm.enP20;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '�������ã�&#10;0��P20&#10;1��BM400,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
